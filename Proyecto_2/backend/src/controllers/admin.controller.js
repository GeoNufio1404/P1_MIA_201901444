const { insertData, getCollection } = require("../config/db.mongo");
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

const NuevoUsuario = async (req, res) => {
    // Recibir los datos enviados desde el cliente
    const { Nombre, Usuario, Correo, Password, TipoUsuario } = req.body;

    // Encriptar contraseña
    const salt = await bcrypt.genSaltSync(10); // Generar un salt || un salt es una cadena aleatoria que se añade a la contraseña antes de encriptarla
    const HashedPassword = await bcrypt.hash(Password, salt); // Encriptar la contraseña

    // Insertar datos a la base de datos
    console.log('Datos recibidos', Nombre, Usuario, Correo, HashedPassword, TipoUsuario);

    // Buscar usuario en la base de datos
    const user = await getCollection('Usuarios', { Usuario: Usuario});

    // Verificar si el usuario ya existe en la base de datos
    if (user.length > 0) {
        return res.status(400).json(
            {
                status: false,
                msg: 'Usuario ya existe',
            });
    };

    const result = await insertData('Usuarios', {
        Nombre,
        Usuario,
        Correo,
        Password: HashedPassword,
        TipoUsuario
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

const ListarUsuarios = async (req, res) => {
    const result = await getCollection('Usuarios');

    if (result instanceof Error) {
        return res.status(500).json(
            {
                status: false,
                msg: 'Error al listar usuarios',
                data: result
            });
    };

    return res.status(200).json(
        {
            status: true,
            msg: 'Listado de usuarios',
            data: result
        });
};

module.exports = {
    ciclo_for,
    NuevoUsuario,
    ListarUsuarios
};