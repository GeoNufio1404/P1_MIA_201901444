
const ciclo_for = async (req, res) => {
    const { numero } = req.params;

    let respuesta = [];

    for (let i = 0; i < numero; i++) {
        respuesta.push(i);
    }

    // Respuesta
    res.status(200).json({ respuesta });
};

module.exports = {
    ciclo_for
};