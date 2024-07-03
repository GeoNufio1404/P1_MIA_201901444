const { insertData, getCollection } = require("../config/db.mongo");
const bcrypt = require('bcryptjs'); // npm i bcryptjs || bcrypt sirve para encriptar contraseñas

const NuevoUsuario = async (req, res) => {
    // Recibir los datos enviados desde el cliente
    const { Nombre, Usuario, Correo, Password } = req.body;
    const TipoUsuario = 'User';

    // Encriptar contraseña
    const salt = await bcrypt.genSaltSync(10); // Generar un salt || un salt es una cadena aleatoria que se añade a la contraseña antes de encriptarla
    const HashedPassword = await bcrypt.hash(Password, salt); // Encriptar la contraseña

    // Insertar datos a la base de datos
    console.log('Datos recibidos', Nombre, Usuario, Correo, HashedPassword, TipoUsuario);

    // Obtener usuario de la base de datos para verificar si ya existe
    const user = await getCollection('Usuarios', { Usuario: Usuario });

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

const ObtenerUsuario = async (req, res) => {

    const user = await getCollection('Usuarios', { Usuario: req.params.Usuario });

    if (user.length == 0) {
        return res.status(404).json(
            {
                status: false,
                msg: 'Usuario no encontrado',
                data: user
            });
    }

    return res.status(200).json(
        {
            status: true,
            msg: 'Usuario encontrado',
            data: user
        });
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
                msg: 'Credenciales incorrectas',
                data: ''
            });
    };

    // Verificar contraseña y usuario
    const validPassword = await bcrypt.compare(Password, user[0].Password);
    const validUser = user[0].Usuario === Usuario;

    if (!validPassword || !validUser) {
        return res.status(401).json(
            {
                status: false,
                msg: 'Credenciales incorrectas',
                data: ''
            });
    };

    // Respuesta
    return res.status(200).json(
        {
            status: true,
            msg: 'Login exitoso',
            data: user[0].TipoUsuario
        });
};

const ActualizarUsuario = async (req, res) => {
    // Recibir los datos enviados desde el cliente
    const { Nombre, Usuario, Correo, Password } = req.body;
    const TipoUsuario = 'User';

    // Encriptar contraseña
    const salt = await bcrypt.genSaltSync(10); // Generar un salt || un salt es una cadena aleatoria que se añade a la contraseña antes de encriptarla
    const HashedPassword = await bcrypt.hash(Password, salt); // Encriptar la contraseña

    // Actualizar datos a la base de datos
    console.log('Datos recibidos', Nombre, Usuario, Correo, HashedPassword, TipoUsuario);

    // Actualizar datos a la base de datos
    const result = await updateData('Usuarios', { Usuario }, {
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
                msg: 'Error al actualizar usuario',
                data: result
            });
    };

    // Respuesta
    return res.status(200).json(
        {
            status: true,
            msg: 'Actualización exitosa',
            data: result
        });
};

module.exports = {
    NuevoUsuario,
    ObtenerUsuario,
    ActualizarUsuario,
    Login
};