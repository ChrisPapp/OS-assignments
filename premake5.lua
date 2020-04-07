workspace "OS-assignment"
    configurations{"Debug", "Release"}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "Pizza"
    kind "ConsoleApp"
    language "C"
    targetdir("bin/" .. outputdir)
    objdir ("bin/obj/" .. outputdir)

    files { "src/**.h", "src/**.c"}

    filter "system:windows"
        includedirs {
            "vendor/pthreads-win32/include/"
        }
        libdirs { "vendor/pthreads-win32/lib/x86/",}
        links { "pthreadVC2" }
        -- copy a file from the objects directory to the target directory
        postbuildcommands {
            "{COPY} vendor/pthreads-win32/dll/x86/pthreadVC2.dll %{cfg.targetdir}"
        }
    filter "system:linux"
        linkoptions { "-pthread" }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "On"
