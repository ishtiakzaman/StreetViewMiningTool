#!/bin/bash

directory="street_view_images_"$(date +%Y_%m_%d_%H_%M_%S)
mkdir $directory

api_key="AIzaSyBTQmmD0KLx8bMU3PFaUosUMcLq9mZDaKo"
count=0

while read -r line
do
  if [[ $line == "#"* ]]
  then
    continue
  fi
  lat=${line%,*}
  lng=${line#*,}
  for ((dir=0;dir<360;dir+=90))
  do
    image_link="https://maps.googleapis.com/maps/api/streetview?"
    image_link+="size=256x256&"
    image_link+="location="${lat}","${lng}"&"
    image_link+="heading="${dir}"&"
    image_link+="pitch=0&"
    image_link+="key="${api_key}
    count=$((count+1))
    wget -O "$directory/sv"$count".jpg" $image_link
  done
done < "$1"
