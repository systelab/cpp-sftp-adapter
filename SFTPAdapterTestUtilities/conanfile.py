import os
from conans import ConanFile, tools, CMake


class SFTPAdapterTestUtilitiesConan(ConanFile):
    name = "SFTPAdapterInterfaceTestUtilities"
    description = "Test utilities for library-agnostic API for C++ to work with SFTP protocol"
    url = "https://github.com/systelab/cpp-sftp-adapter"
    homepage = "https://github.com/systelab/cpp-sftp-adapter"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "sftp", "adapter", "wrapper", "test", "gtest")
    license = "MIT"
    generators = "cmake_find_package"
    settings = "os", "compiler", "build_type", "arch"
    options = {"gtest": ["1.7.0", "1.8.1", "1.10.0"]}
    default_options = "gtest=1.10.0"
    exports_sources = "*"

    def requirements(self):
        if self.options.gtest == "1.7.0":
            self.requires("gtest/1.7.0@systelab/stable")
        elif self.options.gtest == "1.8.1":
            self.requires("gtest/1.8.1")
        else:
            self.requires("gtest/1.10.0")

        self.requires("TestUtilitiesInterface/1.0.5@systelab/stable")
        if ("%s" % self.version) == "None":
            self.requires("SFTPAdapterInterface/%s@systelab/stable" % os.environ['VERSION'])
        else:
            self.requires("SFTPAdapterInterface/%s@systelab/stable" % self.version)

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include/SFTPAdapterInterfaceTestUtilities", keep_path=True)
        self.copy("*SFTPAdapterInterfaceTestUtilities.lib", dst="lib", keep_path=False)
        self.copy("*SFTPAdapterInterfaceTestUtilities.pdb", dst="lib", keep_path=False)
        self.copy("*SFTPAdapterInterfaceTestUtilities.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
