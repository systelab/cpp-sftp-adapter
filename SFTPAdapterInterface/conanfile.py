from conans import ConanFile


class SFTPAdapterInterfaceConan(ConanFile):
    name = "SFTPAdapterInterface"
    description = "Interface of library-agnostic API for C++ to work with SFTP protocol"
    url = "https://github.com/systelab/cpp-sftp-adapter"
    homepage = "https://github.com/systelab/cpp-sftp-adapter"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "sftp", "adapter", "wrapper", "interface")
    license = "MIT"
    generators = "cmake_find_package"
    # No settings/options are necessary, this is header only

    def package(self):
        self.copy("ISFTPClientAdapter.h", dst="include/SFTPAdapterInterface")

    def package_info(self):
        self.info.header_only()
