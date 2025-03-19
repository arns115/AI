const path = require('path');
const { exec } = require('child_process');
const express = require('express');
const { writeToFile, readFromFile } = require('./utils');
const fs = require('fs');

const app = express();
const port = 3000;

app.use(express.static('public'));
app.use(express.json());

app.get('/', (req, res) => {
	res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.post('/scramble-moves', (req, res) => {
	const { moves } = req.body;
	const arr = moves.split(' ');
	let s = `${arr.length}\n`;
	arr.forEach(element => {
		s += `${element}\n`;
	});
	writeToFile(path.join(__dirname, 'cpp'), 'input.txt', s);
	res.status(200);
});

app.get('/solve-moves', (req, res) => {
	const filePath = path.join(__dirname, 'cpp');

	exec(`${filePath}/solver`, { cwd: filePath }, (error, stdout, stderr) => {
    if (error) {
			console.error(`exec error: ${error}`);
			console.error(`stderr: ${stderr}`);
			return res.status(400).json({ status: 'error', message: 'C++ program failed' });
    }

    const outputFilePath = path.join(filePath, 'output.txt');
    fs.readFile(outputFilePath, 'utf8', (err, data) => {
			if (err) {
				console.error(`File read error: ${err}`);
				return res.status(500).json({ status: 'error', message: 'Failed to read output file' });
			}
			console.log('server moves:\n', data);
			const moves = data.trim().split('\n');
			res.status(200).json({ status: 'success', body: { moves } });
    });
	});
});

app.listen(port, () => {
	console.log(`Server running at http://localhost:${port}`);
});
