package sample;

import javafx.collections.FXCollections;
import javafx.scene.chart.*;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import sample.SerialPortService;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import java.io.IOException;
import java.util.concurrent.TimeUnit;

public class Main extends Application {

    private final static int COUNTER = 1 << 10;
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        //Receieve Arduino COM Port from 'SerialPortSerivce.java'
        var sp = SerialPortService.getSerialPort("COM3");
        var outputStream = sp.getOutputStream();

        //Creating GUI
        var pane = new BorderPane();
        var label = new Label();
        var button1 = new Button("System On/Off Toggle");
        var button2 = new Button("Force Door Open");

        pane.setBottom(label);
        pane.setLeft(button1);
        pane.setRight(button2);
        pane.setPadding(new Insets(0, 20, 0, 20));

        //If toggle button is pressed, write the byte 0 to the output stream
        button1.setOnMousePressed(value ->{button1.setText("System On/Off Toggle");
            try {
                outputStream.write(0);
            } catch (IOException e) {
                e.printStackTrace();
            }});
        //If toggle button is released, write the byte 5 to the output stream
        button1.setOnMouseReleased(value ->{button1.setText("System On/Off Toggle");
            try {
                outputStream.write(5);
            } catch (IOException e) {
                e.printStackTrace();
            }});
        //If toggle button is pressed, write the byte 255 to output stream
        button2.setOnMousePressed(value ->{button1.setText("Force Door Open");
            try {
                outputStream.write(255);
            } catch (IOException e) {
                e.printStackTrace();
            }});
        //If toggle button is released, write the byte 5 to the output steram
        button2.setOnMouseReleased(value ->{button1.setText("Force Door Open");
            try {
                outputStream.write(5);
            } catch (IOException e) {
                e.printStackTrace();
            }});
        //Create GUI scene
        var scene = new Scene(pane, 900, 500);

        var controller = new DataController(); // create the controller
        sp.addDataListener(controller);

        primaryStage.setTitle("Door Program");

        //Setting up graph
        var now = System.currentTimeMillis();

        var xAxis = new NumberAxis("Time", now, now + 90000, 1000); // creates the x-axis (which automatically updates)
        var yAxis = new NumberAxis("Door Opens", 0, 10, 1); // creates the y-axis
        //Plot (x,y) points on graph
        //Receiveing points from data controller class
        //Graphs it as a scatter chart
        var series = new XYChart.Series<>(controller.getDataPoints()); // creates the series (all the data)
        var lineChart = new ScatterChart<>(xAxis, yAxis, FXCollections.singletonObservableList(series)); // creates the chart
        lineChart.setTitle("Amount of times the door has been opened.");

        //Create graph GUI scene
        pane.setBottom(lineChart);
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}