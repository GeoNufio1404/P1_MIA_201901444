const { Router } = require("express")
const { check } = require('express-validator')

const validate = require("../middlewares/validateAtributes")
const UsuarioController = require("../controllers/usuario.controller")

const router = Router()


// POST /users - Crear un nuevo usuario
router.post("/", (req, res) => {

    
});


// GET /users/:id - Obtener un usuario por ID
router.get("/:id", (req, res) => {
    const id = req.params.id
    const user = {}
    res.status(200).json(user)

});


// PUT /users/:id - Actualizar un usuario
router.put("/:id", (req, res) => {

    const id = req.params.id
    const { name, email } = req.body

    const updatedUser = { name, email }

    res.status(200).json(updatedUser)

});


// DELETE /users/:id - Eliminar un usuario
router.delete("/:id", (req, res) => {

    const id = req.params.id

    res.status(204).json({ message: "Usuario eliminado" })

});
module.exports = router;