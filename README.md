<h1 align="center">🎷 In The Pocket 🎹</h1>
<div align="center">
  A jazz themed rhythm game with mechanics similar to Guitar Hero. </br>
  Written in M68K ASM and C for the Atari ST in high resolution monochrome mode. </br>
  A semester long project for Computing Machinery II (COMP2659) at Mount Royal University. </br>
</div>

***

![Game Screenshot](https://github.com/lcamp702/InThePocket/blob/media/screenshots/Cover.png)

In the Pocket follows main character Doug as he tries to make a name for himself in the jazz scene. 
The player plays Doug’s songs by pressing the ASDF keys when the notes corresponding to each key reach their target. 
Playing the right notes at the right times plays a tone, builds the crowd’s enjoyment meter, and adds 10x the multiplier to the player score. 
Every 10 consecutive notes increases the point per note multiplier by 1. 
If the player mistimes notes or plays the wrong note, an out of key note will play.
Upon any mistake the multiplier will reset and the crowd enjoyment will decrease. 
With 0 enjoyment, the Doug will be booed off stage and the level will end.

***

## Screenshots
<table>
  <tr>
    <td><img src="https://github.com/lcamp702/InThePocket/blob/media/screenshots/Menu.png"></td>
    <td><img src="https://github.com/lcamp702/InThePocket/blob/media/screenshots/Credits.png"></td>
  </tr>
  <tr>
    <td><img src="https://github.com/lcamp702/InThePocket/blob/media/screenshots/Game1.png"></td>
    <td><img src="https://github.com/lcamp702/InThePocket/blob/media/screenshots/Game3.png"><</td>
  </tr>
  <tr>
    <td><img src="https://github.com/lcamp702/InThePocket/blob/media/screenshots/Win.png"></td>
    <td><img src="https://github.com/lcamp702/InThePocket/blob/media/screenshots/Loss.png"></td>
  </tr>
</table>

***

## Objects

| Object | Struct | Behaviour | Image |
|---|---|---|:---:|
| Meter | INT8 enjoyment<br />UINT32 score<br />INT8 multiplier<br />INT8 multi_progress<br />INT8 dirty | Tracks score, enjoyment, and multiplier | ![Full Sax Meter](https://github.com/lcamp702/InThePocket/blob/media/assets/sax_filled.bmp) ![Full Sax Meter](https://github.com/lcamp702/InThePocket/blob/media/assets/sax_empty.bmp) ![Full Sax Meter](https://github.com/lcamp702/InThePocket/blob/media/screenshots/Score.png) |
| Note | UINT32 time  *Time note appears on screen*<br />UINT8 pitch  *Track note shows up on*<br />UINT8 duration  *Note icon*<br />UINT8 neighbour *Next note plays at the same time*| Stores time for note events | ![Whole Note](https://github.com/lcamp702/InThePocket/blob/media/assets/note_head_whole.bmp)<br />![Half Note](https://github.com/lcamp702/InThePocket/blob/media/assets/note_head_half.bmp)<br />![Black Note](https://github.com/lcamp702/InThePocket/blob/media/assets/note_head_black.bmp) |
| Targets | UINT8 Targets[TARGET_COUNT] | Turn on when the corresponding key is pressed | ![Targets](https://github.com/lcamp702/InThePocket/blob/media/screenshots/Targets.png) |
| Chart | N/A | N/A | ![Chart](https://github.com/lcamp702/InThePocket/blob/media/screenshots/Chart.png) |
  
***

## Progress

- [X] Checkpoint 1  (Game Specification)                          [October 9th]
- [X] Checkpoint 2  (Raster, Render, Model, and Event functions)  [October 19th]
- [X] Checkpoint 3  (Animations, Clock, Non-blocking input)       [November 9th]
- [X] Checkpoint 4  (Sound)                                       [November 25th]
- [ ] Checkpoint 5  (Custom ROM, Drop TOS dependencies)           [December 9th]

