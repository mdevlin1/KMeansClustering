libs = [
    'PocoUtil', 
    'PocoXML', 
    'PocoJSON', 
    'PocoNet', 
    'PocoFoundation',
    'opencv_core',
    'opencv_highgui',
    'opencv_imgcodecs'
]

cxxflags = [
    "-g", 
    "-std=c++17"
]

cpppath = [
    '/usr/include/Poco/',
    '/usr/local/include/opencv2/',
    '/usr/local/lib/'
]

libpath = [
    '/usr/lib/x86_64-linux-gnu/'
]

Program('kmeans', Glob("*.cpp"), LIBS=libs, CXXFLAGS=cxxflags, CPPPATH=cpppath, LIBPATH=libpath)
