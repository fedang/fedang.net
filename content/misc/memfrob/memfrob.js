const encoder = new TextEncoder();
const known = {
    "n": 10,
    "r": 13,
    "t": 9,
    "b": 8,
    "f": 12,
    "v": 11,
    "\\": 92,
    "0": 0,
};

function unescapeBytes(str) {
    const out = [];
    let i = 0;
    let chunk = "";

    while (i < str.length) {
        if (str[i] === "\\") {
            if (chunk) {
                out.push(...encoder.encode(chunk));
                chunk = "";
            }

            if (str[i+1] === "x" && i+3 < str.length) {
                out.push(parseInt(str.slice(i+2, i+4), 16));
                i += 4;
            } else if (str[i+1] in known && i+1 < str.length) {
                out.push(known[str[i]]);
                i += 2
            } else {
                throw new Error("Invalid escape sequence");
            }
        } else {
            chunk += str[i++];
        }
    }

    if (chunk)
        out.push(...encoder.encode(chunk));
    return new Uint8Array(out);
}

function escapeBytes(bytes) {
    return Array.from(bytes).map(b => {
        if (b >= 0x20 && b <= 0x7E)
            return String.fromCharCode(b)

        let k = Object.keys(known).find(k => known[k] === b);
        console.log(k)
        return k !== undefined
            ? `\\${k}`
            : `\\x${b.toString(16).padStart(2,'0')}`;
    }).join('');
}

function parseHex(str) {
    str = str.replace(/\s+/g, "");
    if (str.length % 2 !== 0)
        throw new Error("Hex string has odd length!");

    const bytes = new Uint8Array(str.length / 2);
    for (let i = 0; i < str.length; i += 2) {
        const val = parseInt(str.substr(i, 2), 16);
        if (isNaN(val))
            throw new Error("Invalid hex character");
        bytes[i / 2] = val;
    }
    return bytes;
}

function printHex(bytes) {
    return Array.from(bytes)
        .map(b => b.toString(16).padStart(2, "0"))
        .join(" ");
}

function memfrob(bytes) {
    for (let i = 0; i < bytes.length; i++)
        bytes[i] ^= 42;
    return bytes;
}

const input = document.getElementById('input');
const output = document.getElementById('result');
const btn = document.getElementById('start');

btn.addEventListener("click", () => {
    output.innerHTML = "";
    try {
        const mode = document.querySelector('input[name="mode"]:checked').value;
        let bytes;
        switch (mode) {
            case "str":
                bytes = encoder.encode(input.value);
                output.value = escapeBytes(memfrob(bytes));
                break;

            case "esc":
                bytes = unescapeBytes(input.value);
                output.value = escapeBytes(memfrob(bytes));
                break;

            case "hex":
                bytes = parseHex(input.value);
                output.value = printHex(memfrob(bytes));
                break;
        }
    } catch (error) {
        output.innerHTML = error;
    }
});
