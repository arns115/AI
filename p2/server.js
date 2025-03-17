const path = require('path');
const { exec } = require('child_process');
const express = require('express');
const { writeToFile, readFromFile } = require('./utils');

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
	exec(`${filePath}/solver.exe`, (error, stdout, stderr) => {
		if (error) {
			console.error(`exec error: ${error}`);
			res.status(400).json({ status: 'error' });
		}
	});
	const moves = readFromFile(path.join(__dirname, 'cpp'), 'output.txt');
	console.log('server moves: ', moves);
	res.status(200).json({ staus: 'success', body: { moves } });
});

app.listen(port, () => {
	console.log(`Server running at http://localhost:${port}`);
});
