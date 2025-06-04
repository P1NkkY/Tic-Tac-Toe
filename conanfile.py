from conan import ConanFile
from conan.tools.cmake import cmake_layout

class TicTacToe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("sfml/2.6.2")

    def layout(self):
        cmake_layout(self)