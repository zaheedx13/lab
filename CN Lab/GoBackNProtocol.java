import java.util.Scanner;

public class GoBackNProtocol {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter total number of frames to send: ");
        int totalFrames = sc.nextInt();

        System.out.print("Enter window size: ");
        int windowSize = sc.nextInt();

        System.out.print("Enter the frame number to lose (0 for no loss): ");
        int lostFrame = sc.nextInt();

        int nextFrameToSend = 1;
        int ackExpected = 1;
        boolean lost = false; 

        while (ackExpected <= totalFrames) {
            int endFrame = nextFrameToSend + windowSize - 1;
            if (endFrame > totalFrames) endFrame = totalFrames;

            System.out.println("\nSender: Sending frames " + nextFrameToSend + " to " + endFrame);

            boolean timeout = false;
            for (int i = nextFrameToSend; i <= endFrame; i++) {
                if (i == lostFrame && !lost) {
                    System.out.println("Receiver: Frame " + i + " lost! No ACK sent.");
                    timeout = true;
                    lost = true;  
                    break;            
                } else {
                    System.out.println("Receiver: Frame " + i + " received. Sending ACK " + i);
                    ackExpected = i + 1;
                }
            }

            if (timeout) {
                System.out.println("Sender: Timeout! Resending from frame " + ackExpected);
                nextFrameToSend = ackExpected;
            } else {
                nextFrameToSend = endFrame + 1; 
            }
        }

        System.out.println("\nAll frames sent successfully!");
        sc.close();
    }
}
