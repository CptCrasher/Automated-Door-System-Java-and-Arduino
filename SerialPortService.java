package sample;
import com.fazecast.jSerialComm.SerialPort;

// Allows interfacing between Arduino serial port and Java
public class SerialPortService {
    private SerialPortService() {
    }

    public static SerialPort getSerialPort(String portDescriptor) {
        var sp = SerialPort.getCommPort(portDescriptor);

        sp.setComPortParameters(9600, Byte.SIZE, SerialPort.ONE_STOP_BIT, SerialPort.NO_PARITY);
        sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0);

        // If no port is found throw
        var hasOpened = sp.openPort();
        if (!hasOpened) {
            throw new IllegalStateException("Failed to open port.");
        }

        return sp;
    }
}
