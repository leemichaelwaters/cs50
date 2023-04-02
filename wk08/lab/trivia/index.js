// Run script once DOM is loaded
document.addEventListener('DOMContentLoaded', function() {


    // Check question one
    // Hanlde correct answer
    let correct = document.querySelector('.correct');  // . for class
    correct.addEventListener('click', function() {
        correct.style.backgroundColor = 'green';
        document.querySelector('#feedback1').innerHTML = 'Correct!';
    });

    // Handle incorrect answer
    let incorrects = document.querySelectorAll('.incorrect');
    for (let i = 0; i < incorrects.length; i++) {
        incorrects[i].addEventListener('click', function() {
            incorrects[i].style.backgroundColor = 'red';
            document.querySelector('#feedback1').innerHTML = 'Incorrect';
        });
    }


    // Check question two
    document.querySelector('#check').addEventListener('click', function() {
        let input = document.querySelector('input');
        // Handle incorrect answers
        if (input.value != 'Switzerland')
        {
            input.style.backgroundColor = 'red';
            document.querySelector('#feedback2').innerHTML = 'Incorrect';
        }
        // Handle correct answer
        else
        {
            input.style.backgroundColor = 'green';
            document.querySelector('#feedback2').innerHTML = 'Correct!';
        }
    });
});