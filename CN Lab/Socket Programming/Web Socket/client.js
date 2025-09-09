// client.js
// Simple Node.js WebSocket client that connects and sends two messages.
// Run: node client.js

const WebSocket = require('ws');

const SERVER = 'ws://localhost:8080';
const ws = new WebSocket(SERVER);

ws.on('open', () => {
  console.log('Connected to server');
  ws.send('Hello from Node.js client!');
  ws.send('How are you?');
});

ws.on('message', (data) => {
  console.log('From server:', data.toString());
});

ws.on('close', (code, reason) => {
  console.log(`Disconnected from server (code=${code}${reason && reason.length ? ', reason=' + reason : ''})`);
});

ws.on('error', (err) => {
  console.error('WebSocket error:', err.message || err);
});
