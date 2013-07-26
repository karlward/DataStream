DataStream
==========

Arduino Stream-like library for streams of generic data types

DataStream is an Arduino "Stream-like" library for streams of generic data 
types.  It's like the Stream library, but not 100% compatible due to the 
character-centricity of the Stream library.  In particular, the read() 
method does not return -1 when the stream is empty (because -1 could be 
confused with a valid data item if the stream is storing signed integers, 
for example). 

The API is still being actively developed, so do not consider the API 
stable until there is a 1.x release.  

There is no documentation yet.  It's coming, trust me.  For now, read the header file. 

Credits
=======
Copyright 2013 Karl Ward and contributors.  See the file CREDITS.

C++ Resources
===========================
The C++ FAQ was quite helpful, particularly the section on templates:
- http://www.parashift.com/c++-faq/
- http://www.parashift.com/c++-faq/templates.html

Bruce Eckel's Thinking in C++ was quite helpful. 

