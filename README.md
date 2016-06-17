# Street View Mining Tool

##### \*Warning: Limited usage only due to api registered for *ishtiak.zaman@gmail.com*, which includes a free plan with limited number of access to google map and google street view.

## geo_generator.html
Run the **geo_generator.html** to generate geo locations directly from google map. Features included:
* **Point Selection:** To select single points from the map.
* **Line Selection:** To select points lies within a line from the map. First click on the starting point, then the end point.
* **Delete:** Delete already positioned points.
* **Reset All:** Clean all locations.
* All points can be dragged.
* **Generate Geocodes:** To get the list of latitude, longitude to the result area.
* **Save as File:** To save the geocodes in a file, that would be read by the c++ svtool program to get street view. Also saved geocodes files can be loaded back.
* **Load File:** Load a saved geocodes .csv file.
 

## svtool binary
Run **./svtool -f filename** to get street view images of the geocodes read from the file. Options included:<br/>
Usage: ./svtool<br/>
-f filename<br/>
[-i latitude column in file (default 0)]<br/>
[-j longitude column in file (default 1)]<br/>
[-t delimiter between columns in file (default ',')]<br/>
[-w width (default 640, maximum allowed limit 640)]<br/>
[-h height (default 640, maximum allowed limit 640)]<br/>
[-d direction1,direction2,...,directionn (default 0,90,180,270; 0 is NORTH, 90 is EAST etc.)]<br/>
[-a angle of view (default 90)]<br/>
[-p pitch (default 0)]<br/>
