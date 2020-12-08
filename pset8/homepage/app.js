const numberController = (function() {
    const RandomNumber = function(max) {
        this.max = max;
    }

    RandomNumber.prototype.calcRandom = function() {
        return Math.floor(Math.random() * this.max);
    }

    return {
        getRandomNumber: function(max) {
            return new RandomNumber(max);
        }
    }
})();

const UIController = (function() {
    const DOMstrings = {
        select: 'select',
        mySelect: 'mySelect',
        result: 'result',
        button: 'button'
    }

    const createLabel = function() {
        const label = document.createElement("label");
        label.innerHTML = "Select number";
        return label;
    }

    const createSelectBox = function(max) {
        const select = document.createElement("select");
        select.classList = 'form-control';
        select.id ="mySelect";
        for (let i = 1; i <= max; i++) {
            const option = document.createElement("option");
            option.text = i;
            select.add(option);
        }
        return select;
    }

    return {
        getSelectedNum: function() {
            const mySelect = document.getElementById(DOMstrings.mySelect);
            const selected = parseInt(mySelect.value);
            return selected;
        },
        showResult: function(result, selectedNum, randomNum) {
            const resultSpan = document.getElementById(DOMstrings.result);
            resultSpan.innerText = result;
            resultSpan.innerHTML = `${result} - You selected: ${selectedNum}. Correct: ${randomNum}`;
        },
        createUI: function() {
            const selectBox = createSelectBox(5);
            const label = createLabel();
            const select = document.getElementById(DOMstrings.select);
            select.appendChild(label);
            select.appendChild(selectBox);
        },
        getDOMstrings: function() {
            return DOMstrings;
        }
    }
})();

const controller = (function(UIctrl, numberCtrl) {
    const setupEventListeners = function() {
        const DOM = UIctrl.getDOMstrings();
        console.log(document.querySelector(DOM.button));
        document.querySelector(DOM.button).addEventListener('click', handleSubmit)
    }

    const handleSubmit = function(e) {
        e.preventDefault();
        const getNumber = numberCtrl.getRandomNumber(5);
        const randomNumber = getNumber.calcRandom();

        const selectedNum = UIctrl.getSelectedNum();

        if (selectedNum === randomNumber) {
            UIctrl.showResult('Won!', selectedNum, randomNumber);
        } else {
            UIctrl.showResult('Lost!', selectedNum, randomNumber);
        }
    }

    return {
        init: function() {
            console.log('app has started');
            UIctrl.createUI();
            setupEventListeners();
        }
    }
})(UIController, numberController);

document.addEventListener('DOMContentLoaded', controller.init);