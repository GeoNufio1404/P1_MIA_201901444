const { insertData, getCollection } = require("../config/db.mongo");
const bcrypt = require('bcryptjs'); // npm i bcryptjs || bcrypt sirve para encriptar contraseñas

const NuevoUsuario = async (req, res) => {
    // Recibir los datos enviados desde el cliente
    const { Nombre, Apellido, Usuario, Correo, Password, Imagen } = req.body;
    const TipoUsuario = 'User';

    // Encriptar contraseña
    const salt = await bcrypt.genSaltSync(10); // Generar un salt || un salt es una cadena aleatoria que se añade a la contraseña antes de encriptarla
    const HashedPassword = await bcrypt.hash(Password, salt); // Encriptar la contraseña

    // Insertar datos a la base de datos
    console.log('Datos recibidos', Nombre, Apellido, Usuario, Correo, HashedPassword, TipoUsuario, Imagen);

    const result = await insertData('Usuarios', {
        Nombre,
        Apellido,
        Usuario,
        Correo,
        Password: HashedPassword,
        TipoUsuario,
        Imagen
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

const Perfil = async (req, res) => {
    const { Usuario } = req.params;

    const user = await getCollection('Usuarios', { Usuario });

    if (user.length == 0) {
        return res.status(404).json(
            {
                status: false,
                msg: 'Usuario no encontrado',
                data: user
            });
    }


};

const Login = async (req, res) => {

    // Recibir los datos enviados desde el cliente
    const { Usuario, Password } = req.body;

    // Buscar usuario en la base de datos
    const user = await getCollection('Usuarios', { Usuario });

    if (user.length == 0) {
        return res.status(404).json(
            {
                status: false,
                msg: 'Usuario no encontrado',
                data: user
            });
    };

    // Verificar contraseña
    const validPassword = await bcrypt.compare(Password, user[0].Password);

    if (!validPassword) {
        return res.status(401).json(
            {
                status: false,
                msg: 'Credenciales incorrectas',
                data: user
            });
    };

    // Respuesta
    return res.status(200).json(
        {
            status: true,
            msg: 'Login exitoso',
            data: user.Usuario,
            tipo_usuario: user.TipoUsuario,
        });
};

module.exports = {
    NuevoUsuario,
    Login
};