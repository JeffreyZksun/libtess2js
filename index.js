var libtess2js = null;

// Load the precompiled binary for windows.
if(process.platform == "win32" && process.arch == "x64") {
	libtess2js = require('./bin/winx64/libtess2js');  
} else if(process.platform == "win32" && process.arch == "ia32") {
	libtess2js = require('./bin/winx86/libtess2js');  
} else {
	// Load the new built binary for other platforms.
	libtess2js = require('./build/Release/libtess2js');  
}

module.exports = libtess2js;
