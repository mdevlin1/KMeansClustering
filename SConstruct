libs = [
    'PocoUtil', 
    'PocoXML', 
    'PocoJSON', 
    'PocoNet', 
    'PocoFoundation'
]

cxxflags = [
    "-g", 
    "-std=c++0x"
]

cpppath = [
    '/usr/include/Poco/'
]

libpath = [
    '/usr/lib/x86_64-linux-gnu/'
]

Program('kmeans', Glob("*.cpp"), LIBS=libs, CXXFLAGS=cxxflags, CPPPATH=cpppath, LIBPATH=libpath)
