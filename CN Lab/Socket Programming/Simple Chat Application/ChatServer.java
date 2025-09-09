import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class ChatServer {
    public static void main(String[] args) {
        final int PORT = 12345;

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server started. Waiting for client...");

            try (Socket socket = serverSocket.accept();
                 BufferedReader in = new BufferedReader(
                         new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8));
                 PrintWriter out = new PrintWriter(
                         new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8), true);
                 BufferedReader console = new BufferedReader(
                         new InputStreamReader(System.in, StandardCharsets.UTF_8))) {

                System.out.println("Client connected: " + socket.getInetAddress());

                // Thread to read messages from the client
                Thread readThread = new Thread(() -> {
                    String msg;
                    try {
                        while ((msg = in.readLine()) != null) {
                            System.out.println("Client: " + msg);
                        }
                    } catch (IOException e) {
                        System.out.println("Connection closed.");
                    }
                });
                readThread.start();

                // Main thread sends messages to client
                String serverMsg;
                while ((serverMsg = console.readLine()) != null) {
                    out.println(serverMsg);
                }

            } catch (IOException e) {
                e.printStackTrace();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
