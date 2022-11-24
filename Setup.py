# default libraries
import os;
import sys;
import subprocess;
import platform;
import shutil;

# must-install libraries
import requests;
from tqdm import tqdm;

class Util :

    @classmethod
    def Download(itself, url, path) :

        if(os.path.isfile(path) is True) : return;

        dlrequest = requests.get(url, stream = True);
        dlprogress = int(dlrequest.headers.get("content-lenght", 0));

        with open(path, "wb") as file, tqdm(
            desc = path, total = dlprogress, unit = "iB", unit_scale = True, unit_divisor = 1024,) as bar :
                for data in dlrequest.iter_content(chunk_size = 1024) :
                    size = file.write(data);
                    bar.update(size);
    
    @classmethod 
    def Decompress(itself, file, path) :
        
        if(os.path.isfile(file) is None) : return;
        shutil.unpack_archive(file, path);

class Vulkan :

    vulkansdkversion = "1.2.198.1";
    vulkansdkbinarypath = "Thirdparty/Vulkan";

    @classmethod 
    def Download(cls) :

        if(os.environ.get("VULKAN_SDK") is not None) : return;

        if(os.path.isdir(cls.vulkansdkbinarypath) is False) :
            os.makedirs(cls.vulkansdkbinarypath);

        downloadurl = "";
        downloadedpath = "";

        if(platform.system() == "Windows") :
            downloadurl = f"https://sdk.lunarg.com/sdk/download/{cls.vulkansdkversion}/windows/VulkanSDK-{cls.vulkansdkversion}-Installer.exe";
            downloadedpath = f"{cls.vulkansdkbinarypath}/VulkanSDK-{cls.vulkansdkversion}-Installer.exe";

            Util.Download(downloadurl, downloadedpath);
            os.startfile(os.path.abspath(downloadedpath));

class Premake5 :

    path = "Thirdparty/Premake5";

    @classmethod
    def Download(itself) :

        if(os.path.isdir(f"{itself.path}") is False) : os.makedirs(f"{itself.path}");

        url = "";
        file = "";

        if(platform.system() == "Windows") :
            url = f"https://github.com/premake/premake-core/releases/download/v5.0.0-beta1/premake-5.0.0-beta1-windows.zip";
            file = f"{itself.path}/premake-5.0.0-beta1-windows.zip";

        Util.Download(url, file);
        Util.Decompress(file, itself.path);

    @classmethod
    def Generate(itself) :
        
        if(len(sys.argv) != 2) :
            subprocess.call(f"{itself.path}/premake5 vs2022");
            return;
        
        subprocess.call(f"{itself.path}/premake5 {sys.argv[1]}");

class GLFW :

    @classmethod
    def Clone(itself) :

        if(os.path.isdir("Thirdparty/glfw") is True) : return;

        dir = os.getcwd();
        os.chdir("Thirdparty");
        subprocess.call(f"git clone https://github.com/glfw/glfw glfw");
        os.chdir("glfw");
        subprocess.call(f"git checkout 3.3-stable");
        os.chdir(dir);

class GLM :

    @classmethod
    def Clone(itself) :

        if(os.path.isdir("Thirdparty/glm") is True) : return;

        dir = os.getcwd();
        os.chdir("Thirdparty");
        subprocess.call(f"git clone https://github.com/g-truc/glm glm");
        os.chdir("glm");
        subprocess.call(f"git checkout 0.9.8");
        os.chdir(dir);

Vulkan.Download();
GLFW.Clone();
GLM.Clone();
Premake5.Download();
Premake5.Generate();