from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout

class Containers(ConanFile):
    build_policy: str = "missing"
    settings: tuple[str] = ("os", "compiler", "build_type", "arch")
    generators: tuple[str] = ("CMakeToolchain", "CMakeDeps")

    def requirements(self) -> None:
        self.requires("catch2/3.11.0")

    def build_requirements(self) -> None:
        self.tool_requires("cmake/3.30.0")
        self.tool_requires("ninja/1.11.0")

    def layout(self) -> None:
        cmake_layout(self)

    def build(self) -> None:
        cmake: CMake = CMake(self)
        cmake.configure()
        cmake.build()
