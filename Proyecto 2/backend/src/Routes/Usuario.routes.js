const { Router } = require("express")

const router = Router()

// GET /users - Obtener lista de usuarios
router.get("/", (req, res) => {
    const users = []
    res.status(200).json(users)

});


// POST /users - Crear un nuevo usuario
router.post("/", (req, res) => {
    const { name, email } = req.body
    const newUser = { name, email }
    res.status(201).json(newUser)

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