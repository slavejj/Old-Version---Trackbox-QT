#Trackbox [![Build Status](https://travis-ci.org/TrackboxFoundation/Trackbox.png?branch=master)](https://travis-ci.org/TrackboxFoundation/Trackbox)

Trackbox is a free, open source music library/player designed from the ground up to include an intuitive and well-designed interface with innovative features not seen in any other music player applications.

Trackbox is still undergoing development of its initial release (version 0.0.0) and is not ready for actual use at this point.

It is being developed using C++ and Qt5 for Windows and Linux, and official Mac support in the future.
Trackbox is licensed under the [GPL version 3 licience](https://github.com/TrackboxFoundation/Trackbox/blob/master/LICENSE).

Current work-in-progress design mock-up:
![Alt text](https://dl.dropboxusercontent.com/u/177483060/trackbox_ui_design.png "Design Concept Mockup")

##Installing
###On Ubuntu:
```
sudo apt-add-repository ppa:ubuntu-sdk-team/ppa
sudo apt-get update
sudo apt-get install -qq qtdeclarative5-dev gcc make
git clone https://github.com/TrackboxFoundation/Trackbox.git
cd Trackbox
# for 64 bit systems
/usr/lib/x86_64-linux-gnu/qt5/bin/qmake Trackbox.pro -r -spec linux-g++
#for 32 bit systems
/usr/lib/i686-linux-gnu/qt5/bin/qmake Trackbox.pro -r -spec linux-g++
```

###On Windows (Experimental):
1. Install Qt5 from http://qt-project.org/downloads
2. git clone https://github.com/TrackboxFoundation/Trackbox.git
3. Open up qt creator and select run from the  build options.

##Planned Features: 
These are a list of the  features that must be included before the  next version of trackbox can be released. If you want to add a feature, create a wiki page starting with spec: and create a issue linking to it. For example spec:playlists.  and start a discussion about it. Once something is agreed upon, it could be added to these feature pages.

###Feature Pages:
####[Development Roadmap](https://github.com/TrackboxFoundation/Trackbox/wiki/Planned-Features/)

####[Feature Specifications](https://github.com/TrackboxFoundation/Trackbox/wiki/Feature-Specifications)

##Development

Submitting Changes:
We LOVE pull requests. Feel free to make them. You can also send a git diff file to j@zatigo.com. Please base code off master. Also, we would appreciate it if you test your code on Travis CI before you submit. It’s all set up, all you have to do is hit the on button for the  fork at travis-ci.org.

Branch Structure:

Pre 0.0.0 release:
We will have two branches, master and proposed.
Master will be for small things, proposed for radical new changes.

```
Master
^
|
|
* Proposed
```

Post 0.0.0 release:

After the  0.0.0 release, we will have 3 branches, master, development, and proposed.
Any commit to master is a new release (not necessarily anything we package and post, but something that is ready to be released to the public).

Development takes over as the place to publish the small changes, and proposed is still the  place to put radical new stuff.

```
Master
^
|
|
* Development
|
|
* Proposed
```
