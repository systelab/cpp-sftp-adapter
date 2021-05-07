from conans import ConanFile

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
