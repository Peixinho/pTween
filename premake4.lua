------------------------------------------------------------------
-- premake 4 pTween solution
------------------------------------------------------------------
solution "pTween"
 
    -- Make Directories
    os.mkdir("libs");
    os.mkdir("build");

    newoption {
        trigger = "bin",
        value = "output",
        description = "Choose a output binary file",
        allowed = {
            { "static", "Static Library - Default" },
            { "shared", "Shared Library" }
        }
    }

    newoption {
       trigger     = "x32",
       description = "Build for 32bit - Default Option"
    }

    newoption {
       trigger     = "x64",
       description = "Build for 64bit"
    }

    buildArch = "x32"
    if _OPTIONS["x64"] then
        buildArch = "x64"
    end

    ------------------------------------------------------------------
    -- setup common settings
    ------------------------------------------------------------------
    configurations { "Debug", "Release" }
    platforms { buildArch }
    location "build"

    rootdir = "."
    libName = "pTween"

    includedirs { "include/" }

    project "pTween"
        targetdir "libs"
        
        if _OPTIONS["bin"]=="shared" then
            kind "SharedLib"
        else
            kind "StaticLib"
        end

        language "C++"
        files { "src/**.h", "src/**.cpp", "include/**.h", "include/**.cpp" }

		if os.get() == "windows" and _OPTIONS["bin"]=="shared" then
			defines({"_EXPORT"})
        end

        defines({"UNICODE"})

        configuration "Debug"

            targetname(libName.."d")
            defines({"_DEBUG"})
            flags { "Symbols" }

        configuration "Release"

            flags { "Optimize" }
            targetname(libName)