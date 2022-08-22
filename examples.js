
let activeMap = defaultMap
let activeLayer = "default"

// definitions
// #define KEYS 5
// #define MODS 3
const keys = 5
const mods = 3

function loop() {
    handleLayer(activeMap[activeLayer])
}

function handleLayer(layer, ignoreMods = false) {
    for(let mod = mods; mod >= 0; mod--) {
        for(let i = 0; i < keys; i++) {
            const [modId, ...args] = layer.keys[i]
            if (modId == (!ignoreMods ? mod : 0)) continue

            let key = matrix.getState(i)
            if(key > 0) {
                handleKey(modId, args)
            }
        }
    }
}

function handleKey(modId, ...args) {
    //maps dont exist in cpp so would need to use a switch case or a vector
    const methodMap = {
        0: press,
        1: switchLayer,
        2: tempSwitchLayer
    }

    methodMap[modId](...args)
}

function press(key) {
    sendKeypress(key)
}

function switchLayer(key) {
    activeLayer = key
}

//Ignores the keypress that caused this event and switches to the given layer until the key is released
function tempSwitchLayer(layer) {
    handleLayer(layer, true)
}

const defaultMap = {
    name: 'default',
    layers: [
        'default',
        'winmod',
        'func'
    ],
    layers: {
        default: {
            keys: [
                [0, 'a'],
                [0, 'b'],
                [0, 'c'],
                [0, 'd'],
                [1, 'winmod'],
            ],
        },
        winmod: {
            keys: [
                [0, 'e'],
                [0, 'f'],
                [0, 'g'],
                [0, 'h'],
                [1, 'func'],
            ],
        },
        func: {
            keys: [
                [0, 'i'],
                [0, 'j'],
                [0, 'k'],
                [2, 'func'],
                [1, 'default'],
            ]
        }
    }
}