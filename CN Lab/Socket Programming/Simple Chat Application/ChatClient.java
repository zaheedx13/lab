import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class ChatClient {
    public static void main(String[] args) {
        final String SERVER_IP = "localhost"; // Change to server IP if running on another machine
        final int PORT = 12345;

        try (Socket socket = new Socket(SERVER_IP, PORT);
             BufferedReader in = new BufferedReader(
                     new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8));
             PrintWriter out = new PrintWriter(
                     new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8), true);
             BufferedReader console = new BufferedReader(
                     new InputStreamReader(System.in, StandardCharsets.UTF_8))) {

            System.out.println("Connected to server.");

            // Thread to read messages from the server
            Thread readThread = new Thread(() -> {
                String msg;
                try {
                    while ((msg = in.readLine()) != null) {
                        System.out.println("Server: " + msg);
                    }
                } catch (IOException e) {
                    System.out.println("Connection closed.");
                }
            });
            readThread.start();

            // Main thread sends messages to server
            String clientMsg;
            while ((clientMsg = console.readLine()) != null) {
                out.println(clientMsg);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
