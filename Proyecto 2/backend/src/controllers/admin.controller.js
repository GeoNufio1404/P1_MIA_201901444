const { insertData } = require("../config/db.mongo");

const ciclo_for = async (req, res) => {

    const { numero } = req.params;

    let respuesta = '';

    for (let i = 0; i < numero; i++) {
        if (i == numero) {
            respuesta += i;
        }
        else {
            respuesta += i + ', ';
        }
    }

    res.status(200).json({ msg: respuesta });
};

module.exports = {
    ciclo_for
};