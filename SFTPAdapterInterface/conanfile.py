from conans import ConanFile, tools

class SFTPAdapterInterfaceConan(ConanFile):
	name = "SFTPAdapterInterface"
	description = "Interface of library-agnostic API for C++ to work with SFTP"
	author = "CSW <csw@werfen.com>"
	topics = ("conan", "sftp", "adapter", "wrapper")
	license = "MIT"
	generators = "visual_studio"
	no_copy_source = True
	# No settings/options are necessary, this is header only

	def package(self):
		self.copy("*.h", dst="include/SFTPAdapterInterface", src=".")
		
	def package_id(self):
		self.info.header_only()
