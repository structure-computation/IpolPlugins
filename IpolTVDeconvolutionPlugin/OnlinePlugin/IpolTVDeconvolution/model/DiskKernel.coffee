#
class DiskKernel extends Model
    constructor: () ->
        super()

        @add_attr
            _name: "disk"
            _radius: 1.0
            
        @add_attr
            radius: @_radius
    
    toString: () ->
        @_name.get()
        