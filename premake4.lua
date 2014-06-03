------------------------------------------------------------------
-- premake 4 pTween solution
------------------------------------------------------------------
solution "pTween"
 
    -- Make Directories
    os.mkdir("bin");
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

    ------------------------------------------------------------------
    -- setup common settings
    ------------------------------------------------------------------
    configurations { "Debug", "Release" }
    platforms { "x32" }
    location "build"

    rootdir = "."
    libName = "pTween"

    project "pTween"
        targetdir "libs"
        
        if _OPTIONS["bin"]=="shared" then
            kind "SharedLib"
        else
            kind "StaticLib"
        end

        language "C++"
        files { "src/**.h", "src/**.cpp" }

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

end;