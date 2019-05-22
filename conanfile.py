from conans import ConanFile, MSBuild

class ExampleConan(ConanFile):
    
    def build(self):
        msbuild = MSBuild(self)
        msbuild.build("RSTestRunner.sln")
