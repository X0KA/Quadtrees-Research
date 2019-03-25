I am Joan Marín, student of the Bachelor’s Degree in Video Games by UPC at CITM. This content is generated for the second year’s subject Project 2, under supervision of lecturer Ricard Pillosu.
 
Introduction
Something I like about coding, is that every task can be approached and solved in different ways.
 
In video games, when we want to check collisions, render tile maps, render 3D objects, etc. the first solutions that comes to our mind will usually be an exhaustive search, also called brute force search.
 
As its name says, this algorithms are generally problem-solving, but they scale with the size of candidates they have to check., working OK with a low amount of them but making our game unplayable if the amount is high.
 
For example, in order to check the collisions of the particles of the system in the image, if we used a brute force algorithm, we would check each particlie colliding with the others, no matter their position.


If we are working with a low amount of particles like in this image, we would iterate 72 (8x8) times each frame. But let’s say we are working with 100 particles, we would need 10.000 (100x100) iterations each frame.
 
Now imagine how many iterations we would need in a scene like this one:


