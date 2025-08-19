function routh(poly) {
	if (poly.length < 2) {
		throw new Error("Denominator should be at least 1th grade");
	}

	let half = Math.ceil(poly.length / 2);
	let tab = Array.from(Array(poly.length), _ => Array(half).fill(undefined));

	for (let i = 0; i < half; i++) {
		for (let j = 0; j < 2; j++) {
			tab[j][i] = poly[2*i+j];
		}
	}

	for (let n = 2; n < poly.length; n++) {
		for (let i = 0; tab[n-2][i+1] !== undefined; i++) {
			if (tab[n-1][0] == 0) {
				throw new Error("Zero value in first column");
			}

			if (tab[n-1][i+1] === undefined) {
				tab[n][i] = tab[n-2][i+1];
				continue;
			}

			let det = tab[n-2][0] * tab[n-1][i+1] - tab[n-2][i+1] * tab[n-1][0];
			tab[n][i] = -det / tab[n-1][0];
		}
	}
	return tab;
}

function tab2html(container, tab) {
  let table = document.createElement("table");
  tab.forEach(row => {
    let tr = document.createElement("tr");
    row.forEach(cell => {
      let td = document.createElement("td");
      td.textContent = (cell !== undefined) ? cell.toFixed(3) : "";
      tr.appendChild(td);
    });
    table.appendChild(tr);
  });

  container.appendChild(table);
}


const input = document.getElementById('poly');
const output = document.getElementById('result');
const btn = document.getElementById('start');

btn.addEventListener("click", () => {
	output.innerHTML = "";
	try {
		let poly = input.value
			.split(",")
			.map(s => parseInt(s.trim(), 10))
			.filter(n => !isNaN(n));

		let tab = routh(poly);
		tab2html(output, tab);

		let signs = tab.map(row => Math.sign(row[0]));

		if (signs.includes(1) && signs.includes(-1))
			output.innerHTML += '<span class="outcome">Unstable!</span>';
		else
			output.innerHTML += '<span class="outcome">Stable!</span>';
	} catch (error) {
		output.innerHTML = error;
	}
});
