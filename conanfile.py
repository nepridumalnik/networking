from conan import ConanFile
from conan.tools.cmake import CMake
from conan.tools.cmake import cmake_layout


class NetworkingConan(ConanFile):
    name = "Networking"
    version = "0.1"
    author = "Dudnik Pavel <ne.pridumal.nik@yandex.ru>"
    url = "https://github.com/nepridumalnik/networking"
    description = "A networking library"
    topics = ("network", "library")
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def layout(self) -> None:
        cmake_layout(self)

    def build_requirements(self) -> None:
        self.requires("gtest/[,include_prerelease=True]")

    def build(self) -> None:
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self) -> None:
        cmake = CMake(self)
        cmake.install()

    def package_info(self) -> None:
        self.cpp_info.libs = ["Networking"]
