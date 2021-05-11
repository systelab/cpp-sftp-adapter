import os
from conans import ConanFile

class SFTPClientCLIConan(ConanFile):
	name = "SFTPClientCLI"
	description = "CLI component that uses SFTP library"
	author = "CSW <csw@werfen.com>"
	topics = ("conan", "sftp")
	license = "MIT"
	generators = "visual_studio"
	settings = "os", "compiler", "build_type", "arch"

	def requirements(self):
		self.requires("libssh/0.9.5@systelab/stable")
		
	def imports(self):
		self.copy("*.dll", dst=os.environ["CONAN_BIN_DIR"], src="bin")
