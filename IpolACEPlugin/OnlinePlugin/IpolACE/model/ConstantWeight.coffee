#
class ConstantWeight extends Model
    constructor: () ->
        super()
        
        @add_attr
            _name: "constant (1)"
            
    toString: () ->
        @_name.get()
        