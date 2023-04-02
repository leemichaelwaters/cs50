# My Website
#### Video Demo:  https://youtu.be/PUzE9ZweIJg
#### Description: Personal website to record my notes on tech-related topics.

<br>

This idea for this project was based off of [chrisalbon.com](https://chrisalbon.com/Welcome.com). I wanted a place where I could record my tech-related notes, just like Chris has shared his data science notes.

Prior to this I had stored all my notes in OneNote. This was great for my personal learning, but I wanted to do more. I've been into Andrew Huberman lately and he has talked about how he stresses to his graduate students the importance of a learn, do, teach approach. I've always been strong in the learning, but weaker in the other two. By building this website, it gave me practice in the do, because I had to learn web development concepts unfamiliar to me. Moving forward, I'm hoping this can serve as a medium to do more projects and then teach others what I've learned. By sharing the website publicly, it will force me to solidify my ideas in a professional manner that will be helpful to others. As opposed to OneNote where the notes are only viewable to me and can be recorded in a more slipshod manner.

I originally was going to program this website using Bootstrap, building on concepts used in this course. However, I wanted to deploy my website to GitHub Pages, which is apparently nicely integrated with Jekyll. I liked the design of the [Python Crash Course Resources Site](https://ehmatthes.github.io/pcc_2e/regular_index/) and saw that it used the [Just the Docs](https://just-the-docs.github.io/just-the-docs/) template. I decided to go with this approach.

Building the website using the Just the Docs template, forced me to learn some Jekyll and Ruby. I also got additional practice with Git and deploying a website to GitHub. I'm hoping this website grows in scope as I continue to develop technically, with the ultimate goal of being a resource to others just as Chris' website was a resource to me.

The Just the Docs template is written in Ruby. The website is served locally using Jekyll and Bundler. The `_config.yml` file list configuration settings for the website. For example, this is where I added settings to change the color scheme from light to dark.

`index.html` is the homepage for the website. Further pages are in the `docs` folder. This folder is used to create the navigation structure of the website. For example, `web-dev` contains the home folder `index` and the child folders `jekyll` and `markdown`.

Finally, the website is deployed to GitHub pages via my [remote repository](https://github.com/leemichaelwaters/leemichaelwaters.github.io). Specifically, its build and deployment uses GitHub Actions as the source. Explicit instructions for this step can be found using the Just the Docs documentation.
