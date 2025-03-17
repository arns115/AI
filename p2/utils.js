const path = require('path');
const fs = require('fs');

function writeToFile(directoy, filename, content) {
	if (!fs.existsSync(directoy)) {
		console.log("File doesn't exist");
		return;
	}

	const filePath = path.join(directoy, filename);

	fs.writeFileSync(filePath, content, 'utf8');
	console.log(`Written successfully to ${filename}`);
}

function readFromFile(directory, filename) {
	const filePath = path.join(directory, filename);

	if (!fs.existsSync(filePath)) {
		console.log("File doesn't exist");
		return;
	}

	return fs.readFileSync(filePath, 'utf8');
}

module.exports = { writeToFile, readFromFile };
