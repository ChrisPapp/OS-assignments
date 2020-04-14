workspace "OS-assignment"
    configurations{"Debug", "Release"}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "Pizza"
    kind "ConsoleApp"
    language "C"
    targetdir("bin/" .. outputdir)
    objdir ("bin/obj/" .. outputdir)

    files { "src/**.h", "src/**.c"}
    includedirs { "src/"}

    -- On Visual Studio only, link pthread-win32 library, and include it's headers.
    filter { "system:windows", "action:vs*" }
        includedirs {
            "vendor/pthreads-win32/include/"
        }
	defines "WINDOWS_VS"
        libdirs { "vendor/pthreads-win32/lib/x86/",}
        links { "pthreadVC2" }
        -- copy a file from the objects directory to the target directory
        postbuildcommands {
            "{COPY} vendor/pthreads-win32/dll/x86/pthreadVC2.dll %{cfg.targetdir}"
        }
    filter "action:gmake*"
        linkoptions { "-pthread" }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "On"
