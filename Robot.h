class Robot
{
public:
    void draw() {
        //Drawing a snowman
        //head
        uLCD.filled_rectangle(xPosition-2, yPosition-2, xPosition+4, yPosition+4, WHITE);
        //eyes
        uLCD.pixel(xPosition-1, yPosition+1, RED);
        uLCD.pixel(xPosition+1, yPosition+1, RED);
        //body
        uLCD.filled_rectangle(xPosition-4, yPosition + 12, xPosition + 6, yPosition +6, WHITE);
        uLCD.filled_rectangle(xPosition-6, yPosition + 24, xPosition + 8, yPosition +14, WHITE);
        //buttons
        uLCD.pixel(xPosition+1, yPosition+7, BLACK);
        uLCD.pixel(xPosition+1, yPosition+9, BLACK);
        uLCD.pixel(xPosition+1, yPosition+11, BLACK);
        //Biceps
        uLCD.line(xPosition -5, yPosition + 8, xPosition - 10, yPosition + 8, RED);
        uLCD.line(xPosition +7, yPosition + 8, xPosition + 12, yPosition + 8, RED);
    }
    void erase() {
        //head
        uLCD.filled_rectangle(xPosition-2, yPosition-2, xPosition+4, yPosition+4, BLACK);
        //eyes
        uLCD.pixel(xPosition-1, yPosition+1, BLACK);
        uLCD.pixel(xPosition+1, yPosition+1, BLACK);
        //body
        uLCD.filled_rectangle(xPosition-4, yPosition + 12, xPosition + 6, yPosition +6, BLACK);
        uLCD.filled_rectangle(xPosition-6, yPosition + 24, xPosition + 8, yPosition +14, BLACK);
        //Biceps
        uLCD.line(xPosition -5, yPosition + 8, xPosition - 10, yPosition + 8, BLACK);
        uLCD.line(xPosition +7, yPosition + 8, xPosition + 12, yPosition + 8, BLACK);
    }
    void moveForward(int distance) {
        yPosition += distance;
    }
    void moveBackward(int distance) {
        yPosition -= distance;
    }
    void moveLeft(int distance) {
        xPosition -= distance;
    }
    void moveRight(int distance) {
        xPosition += distance;
    }
    //Makes the initial position the center of the screen
    Robot() {
        xPosition = 63;
        yPosition = 63;
    }
private:
    int xPosition;
    int yPosition;
};
