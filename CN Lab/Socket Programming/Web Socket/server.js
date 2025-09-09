// server.js
// Simple WebSocket server using the "ws" library.
// Run: node server.js

const WebSocket = require('ws');

const PORT = 8080;
const wss = new WebSocket.Server({ port: PORT });

console.log(`WebSocket server running on ws://localhost:${PORT}`);

wss.on('connection', (ws, req) => {
  const clientAddr = `${req.socket.remoteAddress}:${req.socket.remotePort}`;
  console.log(`New client connected: ${clientAddr}`);

  // Send a welcome message to the client
  ws.send('Welcome! You are connected to the Node.js WebSocket server.');

  // When the server receives a message from this client
  ws.on('message', (message) => {
    const text = message.toString();
    console.log(`Received from ${clientAddr}: ${text}`);

    // Echo the message back to the same client
    ws.send(`echo: ${text}`);
  });

  ws.on('close', (code, reason) => {
    console.log(`Client ${clientAddr} disconnected (code=${code}${reason && reason.length ? ', reason=' + reason : ''})`);
  });

  ws.on('error', (err) => {
    console.error(`Client ${clientAddr} error:`, err);
  });
});
