add_rules("mode.debug", "mode.release")

add_requires("imgui docking", {configs = {glfw = true, opengl3 = true}, system = false})
add_requires("glfw", "glad", "implot-homemade", "stb", "spdlog", {system = false})

target("p_interface")
    set_kind("shared")
    set_languages("c++20")
    add_files("src/**.cpp")
    add_includedirs("src")
    add_packages("glfw", "glad", "imgui docking", "implot-homemade", "stb", "spdlog")

target("p_interface_test")
    set_default(false)
    set_kind("binary")
    set_languages("c++20")
    add_files("src/**.cpp", "test/**.cpp")
    add_includedirs("src")
    add_packages("glfw", "glad", "imgui docking", "implot-homemade", "stb", "spdlog")

package("implot-homemade")
    set_homepage("https://github.com/epezent/implot")
    set_description("Immediate Mode Plotting")
    set_license("MIT")

    add_urls("https://github.com/epezent/implot/archive/refs/tags/$(version).tar.gz",
             "https://github.com/epezent/implot.git")

    add_versions("v0.16", "961df327d8a756304d1b0a67316eebdb1111d13d559f0d3415114ec0eb30abd1")
    add_versions("v0.15", "3df87e67a1e28db86828059363d78972a298cd403ba1f5780c1040e03dfa2672")

    add_deps("imgui docking", {configs = {glfw = true, opengl3 = true}, system = false})

    on_install("windows", "linux", "macosx", "mingw", "android", "iphoneos", function (package)
        local configs = {}
        io.writefile("xmake.lua", [[
            add_requires("imgui docking", {configs = {glfw = true, opengl3 = true}, system = false})
            add_rules("mode.release", "mode.debug")
            target("implot")
                set_kind("$(kind)")
                set_languages("c++11")
                add_files("*.cpp")
                add_headerfiles("*.h")
                add_packages("imgui")
                if is_plat("windows") and is_kind("shared") then
                    add_rules("utils.symbols.export_all", {export_classes = true})
                end
        ]])
        if package:config("shared") then
            configs.kind = "shared"
        end
        import("package.tools.xmake").install(package, configs)
    end)

    on_test(function (package)
        assert(package:check_cxxsnippets({test = [[
            #include <implot.h>
            void test() {
                ImPlot::CreateContext();
                ImPlot::DestroyContext();
            }
        ]]}, {configs = {languages = "c++11"}}))
    end)