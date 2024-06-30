const { insertData } = require("../config/db.mongo");
const bcrypt = require('bcryptjs'); // npm i bcryptjs || bcrypt sirve para encriptar contraseñas

const ciclo_for = async (req, res) => {

    const { numero } = req.params;

    let respuesta = '';

    for (let i = 0; i <= numero; i++) {
        if (i == numero) {
            respuesta += i;
        }
        else {
            respuesta += i + ', ';
        }
    }

    res.status(200).json({ msg: respuesta });
};

const registro = async (req, res) => {
    // Recibir los datos enviados desde el cliente
    const { nombre, apellido, usuario, correo, password } = req.body;

    // Encriptar contraseña
    const salt = await bcrypt.genSaltSync(10); // Generar un salt || un salt es una cadena aleatoria que se añade a la contraseña antes de encriptarla
    const HashedPassword = await bcrypt.hash(password, salt); // Encriptar la contraseña

    // Insertar datos a la base de datos
    console.log('Datos recibidos', nombre, apellido, usuario, correo, HashedPassword);


    const result = await insertData('Usuarios', {
        nombre,
        apellido,
        usuario,
        correo,
        password: HashedPassword
    });


    if (result instanceof Error) {
        return res.status(500).json(
            {
                status: false,
                msg: 'Error al registrar usuario',
                data: result
            });
    };

    // Respuesta
    return res.status(200).json(
        {
            status: true,
            msg: 'Registro exitoso',
            data: result
        });
};


module.exports = {
    ciclo_for,
    registro
};