## Description
This Program allows you to play two songs, play the solfa method going to the
highest not then back to the lowest note, and completely stop the song that is
playing. This is Done by pressing 4 buttons on the green board.

Press S1 to play America (My Country, 'Tis of Thee).

Press S2 to play This Is Halloween.

Press S3 to play the notes from the solfa method.

Press S4 to stop the buzzer and turn off the LEDs.

## Notes
1) When the msp430 plays a song, it will have the green LED turn on if it
plays a note and turns on the red LED when it is at rest.

2) The buzzer and LEDs will quickly be turned off to represent a transition to
the next beat in the song.

3) When the buzzer plays the solfa method higher notes will be dimmer than the
lower notes so that means the green LED will get dimmer the higher the
frequency gets and brighter as it gets lower.

4) After you stop a song with S4, when you try to play the same song it will
start from the beginning, not where you left off.
