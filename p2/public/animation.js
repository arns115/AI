const scrambleInput = document.getElementById('input_scramble-moves');
const scrambleButton = document.getElementById('button_scramble');
const moveDurationInput = document.getElementById('input_move-duration');
const resetButton = document.getElementById('button_reset');
const solveButton = document.getElementById('button_solve');

let scene = new THREE.Scene();
let camera = new THREE.PerspectiveCamera(75, 1 / 1, 0.1, 1000);
let renderer = new THREE.WebGLRenderer({ antialias: true, alpha: true });
renderer.setSize(800, 800);
document.body.appendChild(renderer.domElement);

let geometry = new THREE.BoxGeometry();
let material = new THREE.MeshBasicMaterial({
	color: 0x00ff00,
	wireframe: true,
});
let cube = new THREE.Mesh(geometry, material);
scene.add(cube);

camera.position.z = 5;

// Animation Loop
function animate() {
	requestAnimationFrame(animate);
	cube.rotation.x += 0.01;
	cube.rotation.y += 0.01;
	renderer.render(scene, camera);
}
animate();

const colors = {
	right: 0x06d001,
	front: 0xff2929,
	left: 0x0d92f4,
	bottom: 0xffeb00,
	top: 0xeeeeee,
	back: 0xff6500,
};

function createCubie() {
	const geometry = new THREE.BoxGeometry(1, 1, 1); // Size of each cubie
	const materials = [
		new THREE.MeshBasicMaterial({ color: colors.front }), // Front face (green)
		new THREE.MeshBasicMaterial({ color: colors.back }), // Back face (red)
		new THREE.MeshBasicMaterial({ color: colors.left }), // Left face (blue)
		new THREE.MeshBasicMaterial({ color: colors.right }), // Right face (yellow)
		new THREE.MeshBasicMaterial({ color: colors.top }), // Top face (white)
		new THREE.MeshBasicMaterial({ color: colors.bottom }), // Bottom face (orange)
	];

	const cubie = new THREE.Mesh(geometry, materials);

	let edges = new THREE.EdgesGeometry(geometry);
	let lineMaterial = new THREE.LineBasicMaterial({
		color: 0x000000,
		linewidth: 10,
	});
	let outline = new THREE.LineSegments(edges, lineMaterial);

	cubie.add(outline);

	return cubie;
}

let cubies = [];
let offset = 1.0;

function getQuaternion(axis, angle) {
	let vx = axis == 'x',
		vy = axis == 'y',
		vz = axis == 'z';
	let quaternion = new THREE.Quaternion();
	quaternion.setFromAxisAngle(new THREE.Vector3(vx, vy, vz), angle);
	return quaternion;
}

for (let x = -1; x <= 1; x++) {
	for (let y = -1; y <= 1; y++) {
		for (let z = -1; z <= 1; z++) {
			let cubie = createCubie();
			cubie.position.set(x * offset, y * offset, z * offset);
			cubie.userData.initialPosition = cubie.position.clone();
			cubie.userData.initialRotation = cubie.rotation.clone();
			cubies.push(cubie);
			scene.add(cubie);
		}
	}
}

let moveQueue = [];
let isRotating = false;
let moveDuration = 200;

const moveDefinitions = {
	R: { axis: 'x', position: offset, direction: -Math.PI / 2 },
	"R'": { axis: 'x', position: offset, direction: Math.PI / 2 },
	L: { axis: 'x', position: -offset, direction: Math.PI / 2 },
	"L'": { axis: 'x', position: -offset, direction: -Math.PI / 2 },
	U: { axis: 'y', position: offset, direction: -Math.PI / 2 },
	"U'": { axis: 'y', position: offset, direction: Math.PI / 2 },
	D: { axis: 'y', position: -offset, direction: Math.PI / 2 },
	"D'": { axis: 'y', position: -offset, direction: -Math.PI / 2 },
	F: { axis: 'z', position: offset, direction: -Math.PI / 2 },
	"F'": { axis: 'z', position: offset, direction: Math.PI / 2 },
	B: { axis: 'z', position: -offset, direction: Math.PI / 2 },
	"B'": { axis: 'z', position: -offset, direction: -Math.PI / 2 },
	// M: { axis: 'x', position: 0, direction: Math.PI / 2 },
	// "M'": { axis: 'x', position: 0, direction: -Math.PI / 2 },
	// E: { axis: 'y', position: 0, direction: Math.PI / 2 },
	// "E'": { axis: 'y', position: 0, direction: -Math.PI / 2 },
	// S: { axis: 'z', position: 0, direction: -Math.PI / 2 },
	// "S'": { axis: 'z', position: 0, direction: Math.PI / 2 },
};

function rotateLayer(move, callback) {
	if (!moveDefinitions[move] || isRotating) return;

	isRotating = true;
	let { axis, position, direction } = moveDefinitions[move];

	let affectedCubies = cubies.filter(
		cube => Math.abs(cube.position[axis] - position) < 0.1
	);
	let group = new THREE.Group();

	affectedCubies.forEach(cube => {
		cube.parent.remove(cube);
		group.add(cube);
	});

	scene.add(group);
	let start = null;
	function animateRotation(timestamp) {
		if (!start) start = timestamp;
		let progress = (timestamp - start) / moveDuration;
		if (progress < 1) {
			group.rotation[axis] = progress * direction;
			requestAnimationFrame(animateRotation);
		} else {
			group.rotation[axis] = direction;
			finalizeRotation();
			isRotating = false;
			callback();
		}
		renderer.render(scene, camera);
	}

	function finalizeRotation() {
		let newCubies = [];
		affectedCubies.forEach(cube => {
			cube.position.applyMatrix4(group.matrix);
			cube.position.round();

			cube.quaternion.premultiply(getQuaternion(axis, direction));

			scene.add(cube);
			newCubies.push(cube);
		});

		scene.remove(group);
	}
	requestAnimationFrame(animateRotation);
}

function processMoveQueue() {
	if (moveQueue.length > 0 && !isRotating) {
		let move = moveQueue.shift();
		rotateLayer(move, processMoveQueue);
	}
}

function executeMoves(sequence) {
	moveQueue = sequence.split(' ');
	processMoveQueue();
}

let isDragging = false;
let previousMouseX = 0;
let previousMouseY = 0;

document.querySelector('canvas').addEventListener('mousedown', event => {
	isDragging = true;
	previousMouseX = event.clientX;
	previousMouseY = event.clientY;
});

window.addEventListener('mousemove', event => {
	if (!isDragging) return;

	let deltaX = event.clientX - previousMouseX;
	let deltaY = event.clientY - previousMouseY;

	scene.rotation.y += deltaX * 0.01;
	scene.rotation.x += deltaY * 0.01;

	previousMouseX = event.clientX;
	previousMouseY = event.clientY;

	renderer.render(scene, camera);
});

window.addEventListener('mouseup', () => {
	isDragging = false;
});

// interaction logic
function randomInt(min, max) {
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

let keyCounter = 0;
let keys = [];
for (const key in moveDefinitions) {
	keyCounter++;
	keys.push(key);
}

function scramble(moveCnt) {
	let moves = [];
	let lastMove = 'c';
	for (let i = 0; i < moveCnt; i++) {
		let index = randomInt(0, keyCounter - 1);
		while (
			keys[index].includes(lastMove[0]) &&
			keys[index].length != lastMove.length
		)
			index = randomInt(0, keyCounter - 1);
		moves.push(keys[index]);
		lastMove = keys[index];
	}

	executeMoves(moves.join(' '));
	solveButton.disabled = false;
	resetButton.disabled = false;
	sendScrambleMoves(moves.join(' '));
}

/*  SERVER API */
async function sendScrambleMoves(moves) {
	try {
		const response = await fetch('http://localhost:3000/scramble-moves', {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
			},
			body: JSON.stringify({ moves }),
		});
	} catch (e) {
		console.error(`Unable to send moves to server: ${e}`);
	}
}

async function getSolveMoves() {
	try {
		const response = await fetch('http://localhost:3000/solve-moves');
		const res = await response.json();
		const arr = res.body.moves.split('\n');
		console.log(arr);
		// executeMoves(res.body.moves);
		scrambleButton.disabled = false;
	} catch (e) {
		console.error(`Couldn't retrieve solve moves: ${e}`);
	}
}

/* SERVER API END */

scrambleButton.addEventListener('click', () => {
	const scrambleMoves = scrambleInput.value;
	if (!scrambleMoves) return;

	scramble(scrambleMoves);
});

moveDurationInput.addEventListener('change', e => {
	moveDuration = e.target.value;
});

resetButton.addEventListener('click', () => {
	cubies.forEach(cubie => {
		cubie.position.copy(cubie.userData.initialPosition);
		cubie.rotation.copy(cubie.userData.initialRotation);
	});
});

solveButton.addEventListener('click', () => {
	solveButton.disabled = true;
	scrambleButton.disabled = true;
	resetButton.disabled = true;
	getSolveMoves();
});

resetButton.addEventListener('click', () => {
	resetButton.disabled = true;
	solveButton.disabled = true;
});
