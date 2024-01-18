# _Look Me in the Eyes II_

~      ~
<br><br><br>
## Technical Approach
For _Look Me in the Eyes II_, my appraoch was to essentially use the image processor from _Look Me in the Eyes I_ on each frame of incoming video. This turned out to be a lot easier than I thought, so this section will be signifigantly shorter than the corresponding section for _Look Me in the Eyes I_. To use the image processor on each frame of the incoming video, all I needed to do was change the buffer I was mapping pixels into to be an ofPixels object instead of an ofImage. I then just used this object to load the next frame of the output video.
### A word on sorting algorithms
As it turns out, the threshold for how fast the sorting algorithm I had to use for the video processor was a lot higher than I expected, so the choice between sorting algorithms does not effect performance in the capacity that I thought it would. In other words, the choice between sorting algorithms (as long as they are sufficiently fast) can completely be based on aesthetics. With this in mind, I chose to use counting sort on the target image and intro sort on the source frame (the combination of sorting algorithms that I found most aesthetically pleasing from _Look Me in the Eyes I_).

## Results
Just as with _Look Me in the Eyes I_, the result is not as exciting with a well-lit source. That being said, the results with a poorly lit source or a source with a lot of color are very interesting two look at. Below I have two different recordings of the processor working (you can see the source in the top left corner of the recordings), the first is me "showing" the processor a number of items and just messing around with it and the second is me "showing" it colored LED lights:

https://github.com/maxcheever/lookmeintheeyes2/assets/74006882/0db615df-79ae-4cc0-98b7-63349646cb37


<br><br><br>
This project is the second of three parts of DART 496, an image/video processing and remix theory independent study with [Professor Eduardo Navas](http://navasse.net/docs/index.php). Resources used for _Look Me in the Eyes I_ include the openFrameworks [graphics](https://openframeworks.cc/documentation/graphics/) and [video](https://openframeworks.cc/documentation/video/) documentation and the chapter ["Image Processing and Computer Vision" from _ofBook_](https://openframeworks.cc/ofBook/chapters/image_processing_computer_vision.html)

