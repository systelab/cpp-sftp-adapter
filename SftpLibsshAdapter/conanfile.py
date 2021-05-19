import os
from conans import ConanFile, tools

class SFTPLibSSHAdapterConan(ConanFile):
	name = "SFTPLibSSHAdapter"
	description = "C++ Wrapper over libssh library to work with sftp"
	author = "CSW <csw@werfen.com>"
	topics = ("conan", "sftp")
	license = "MIT"
	generators = "visual_studio"
	settings = "os", "compiler", "build_type", "arch"

	def requirements(self):
		self.requires("libssh/0.9.5@systelab/stable")
		
	def package(self):
		self.copy("*.h", dst="include/SFTPLibSSHAdapter", src=".")
		self.copy("SFTPLibSSHAdapter.lib", dst="lib", src=os.environ["CONAN_LIB_DIR"])
		self.copy("SFTPLibSSHAdapter.dll", dst="bin", src=os.environ["CONAN_BIN_DIR"])
		self.copy("SFTPLibSSHAdapter.pdb", dst="bin", src=os.environ["CONAN_BIN_DIR"])
		
	def package_info(self):
		self.cpp_info.libs = tools.collect_libs(self)
