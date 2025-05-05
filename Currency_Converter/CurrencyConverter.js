const select = document.getElementById("currencySelect");
const resultDisplay = document.getElementById("result");
const inputAmount = document.getElementById("currencyInput");
const convertButton = document.getElementById("convertButton");

(async() => {
    try {
        const res = await fetch("https://api.exchangerate.host/symbols");
        const data = await res.json();
        console.log("Symbols response:", data); // Debug

        const symbols = data.symbols;

        const defaultOption = document.createElement("option");
        defaultOption.value = "";
        defaultOption.textContent = "Select a currency...";
        defaultOption.disabled = true;
        defaultOption.selected = true;
        select.appendChild(defaultOption);

        for (const code in symbols) {
            const option = document.createElement("option");
            option.value = code;
            option.textContent = `${code} - ${symbols[code].description}`;
            select.appendChild(option);
        }
    } catch (error) {
        console.error("Error loading symbols:", error);
        resultDisplay.textContent = "Failed to load currency list.";
    }
})();

convertButton.addEventListener("click", async() => {
    const amount = parseFloat(inputAmount.value);
    const currency = select.value;

    if (!currency) {
        resultDisplay.textContent = "Please select a currency.";
        return;
    }

    if (isNaN(amount) || amount <= 0) {
        resultDisplay.textContent = "Please enter a valid amount.";
        return;
    }

    try {
        const response = await fetch(`https://api.exchangerate.host/latest?base=USD&symbols=${currency}`);
        const data = await response.json();
        console.log("Conversion API response:", data);

        const rate = (data.rates || {})[currency];

        if (!rate) {
            resultDisplay.textContent = "Invalid currency selected or no rate found.";
            return;
        }

        const converted = amount * rate;
        resultDisplay.textContent = `Converted Amount: ${currency} ${converted.toFixed(2)} (Live Rate)`;
    } catch (error) {
        console.error("Conversion error:", error);
        resultDisplay.textContent = "Failed to convert currency.";
    }
});