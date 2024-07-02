const { Router } = require("express")
const { check } = require('express-validator')

const validate = require("../middlewares/validateAtributes")
const UsuariosController = require("../controllers/usuarios.controller")

const router = Router()

// GET / - Mostrar mensaje de bienvenida
router.get("/", (req, res) => {
    res.status(200).json({ message: 'Es' });
});

// POST /users - Crear un nuevo usuario
router.post("/", [
    check('Nombre', 'El nombre es obligatorio').notEmpty(),
    check('Usuario', 'El usuario es obligatorio').notEmpty(),
    check('Correo', 'El email es obligatorio').isEmail(),
    check('Password', 'El password es obligatorio').notEmpty(),
    validate
], UsuariosController.NuevoUsuario); 


// GET /users/:id - Obtener un usuario por ID
router.get("/:id", UsuariosController.ObtenerUsuario);

// GET /login - Iniciar sesión
router.post("/login", [
    check('Usuario', 'El usuario es obligatorio').notEmpty(),
    check('Password', 'El password es obligatorio').notEmpty(),
    validate
], UsuariosController.Login);

// PUT /users/:id - Actualizar un usuario
router.put("/:id", [
    check('Nombre', 'El nombre es obligatorio').notEmpty(),
    check('Usuario', 'El usuario es obligatorio').notEmpty(),
    check('Correo', 'El email es obligatorio').isEmail(),
    check('Password', 'El password es obligatorio').notEmpty(),
    validate
], UsuariosController.ActualizarUsuario);


module.exports = router;